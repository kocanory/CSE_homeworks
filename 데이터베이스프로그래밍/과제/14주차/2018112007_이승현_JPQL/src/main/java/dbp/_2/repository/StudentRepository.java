package dbp._2.repository;

import dbp._2.entity.Student; // Student.java 경로
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

public interface StudentRepository extends JpaRepository<Student, Long> {
    @Query(value = "from Student where id = ?1") // id로 검색
    public Optional<Student> findStudentById(Long id);
    @Query(value = "from Student where name = ?1") // name으로 검색
    public List<Student> findStudentByName(String name);
    @Modifying // address 수정
    @Query(value = "update Student set address = ?2 where id = ?1", nativeQuery = true)
    @Transactional
    public void updateStudentAddress(Long id, String address);
    @Modifying // 데이터 삭제
    @Query(value = "delete from Student where id = ?1")
    @Transactional
    public void deleteStudentById(Long id);
    @Modifying // 데이터 삽입
    @Query(value = "insert into Student(id, name, address, did) values(?1, ?2, ?3, ?4)",
            nativeQuery = true)
    @Transactional
    public void insertStudent(Long id, String name, String address, Long did);

    @Query(value = "select s from Student s join fetch s.dept") // 전체 조회
    public List<Student> findAll();
}




