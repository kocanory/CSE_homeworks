package dbp.UnivQuerydsl.repository.impl;

import dbp.UnivQuerydsl.entity.Student; // Student.java 경로
import com.querydsl.jpa.impl.JPAQueryFactory;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.support.QuerydslRepositorySupport;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

import static dbp.UnivQuerydsl.entity.QDept.dept;
import static dbp.UnivQuerydsl.entity.QStudent.student;

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
}



