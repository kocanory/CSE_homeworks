package dbp._2.repository.impl;

import dbp._2.entity.Student; // Student.java 경로
import com.querydsl.jpa.impl.JPAQueryFactory;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.support.QuerydslRepositorySupport;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

import java.util.Iterator;
import java.util.List;

import static dbp._2.entity.QDept.dept;
import static dbp._2.entity.QStudent.student;

@Repository
public class StudentRepositoryImpl extends QuerydslRepositorySupport {
    private final JPAQueryFactory jpaQueryFactory;

    public StudentRepositoryImpl(JPAQueryFactory jpaQueryFactory) {
        super(Student.class);
        this.jpaQueryFactory = jpaQueryFactory;
    }

    public Student findStudentById(Long id) { // id로 조회
        return jpaQueryFactory
                .selectFrom(student)
                .where(student.id.eq(id))
                .fetchOne();
    }
    public List<Student> findStudentByName(String name) { // name으로 조회
        return jpaQueryFactory
                .selectFrom(student)
                .where(student.name.eq(name))
                .fetch();
    }
    public void updateStudentAddress(Long id, String address) { // address 수정
        long execute = jpaQueryFactory
                .update(student)
                .set(student.address, address)
                .where(student.id.eq(id))
                .execute();
    }
    public void deleteStudentById(Long id){ // 데이터 삭제
        long execute = jpaQueryFactory
                .delete(student)
                .where(student.id.eq(id))
                .execute();
    }
    public void saveAll(List<Student> students) { // 행 삽입
        Iterator<Student> iter = students.iterator();
        while(iter.hasNext())
        {
            Student s = iter.next();
            long execute = jpaQueryFactory
                .insert(student)
                .values(s.getId(), s.getName(), s.getAddress(), s.getDept().getId())
                .execute();
        }
    }

    public List<Student> getAllStudents() { // 전체 조회
        return jpaQueryFactory
                .select(student)
                .distinct()
                .from(student)
                .innerJoin(student.dept,dept)
                .fetchJoin().fetch();
    }
}



