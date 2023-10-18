package dbp._2.repository.impl;

import dbp._2.entity.Dept; // Dept.java 경로
import com.querydsl.jpa.impl.JPAQueryFactory;
import org.springframework.data.jpa.repository.support.QuerydslRepositorySupport;
import org.springframework.stereotype.Repository;

import java.util.List;

import static dbp._2.entity.QDept.dept;

@Repository
public class DeptRepositoryImpl extends QuerydslRepositorySupport {
    private final JPAQueryFactory jpaQueryFactory;

    public DeptRepositoryImpl(JPAQueryFactory jpaQueryFactory) {
        super(Dept.class);
        this.jpaQueryFactory = jpaQueryFactory;
    }

    public Dept findDeptByName(String name) { // name으로 조회
        return jpaQueryFactory
                .selectFrom(dept)
                .where(dept.name.eq(name))
                .fetchOne();
    }

    public List<Dept> findDeptByBuilding(String building) { // building으로 조회
        return jpaQueryFactory
                .selectFrom(dept)
                .where(dept.building.eq(building))
                .fetch();
    }
}


